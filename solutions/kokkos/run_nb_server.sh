#!/bin/bash
#
# Usage: ./run_nb_server PORT PASSWORD

module load anaconda/python3

echo "Create a tunnel over ssh from your workstation to Cirrus with:"
echo "ssh -NL 8888:0.0.0.0:$1 $USER@login.cirrus.ac.uk"
echo "Then point your browser at http://localhost:8888/notebooks/plot.ipynb"

jupyter-notebook --no-browser --ip=0.0.0.0 --port $1 --NotebookApp.token=$2

