EXE_NAME = "02_Exercise"

default : $(EXE)

SRC = $(wildcard *.cpp)

CXXFLAGS = -O3
LINK = $(CXX)

DEPFLAGS = -M

OBJ = $(SRC:.cpp=.$(KOKKOS_DEVICES).o)

include $(KOKKOS_PATH)/Makefile.kokkos

$(EXE): $(OBJ) $(KOKKOS_LINK_DEPENDS)
	$(LINK) $(KOKKOS_LDFLAGS) $(EXTRA_PATH) $(OBJ) $(KOKKOS_LIBS) -o $(EXE)

clean: 
	rm -f *.o *.cuda *.host

# Compilation rules

%.$(KOKKOS_DEVICES).o:%.cpp $(KOKKOS_CPP_DEPENDS)
	$(CXX) $(KOKKOS_CPPFLAGS) $(KOKKOS_CXXFLAGS) $(CXXFLAGS) $(EXTRA_INC) -c $< -o $@

