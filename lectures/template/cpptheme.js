import {epcc, Theme} from "https://EPCCed.github.io/remark_theme/latest.js";

var footer = new URL(import.meta.url).searchParams.get("footer");

if (!footer) {
    footer = "&copy; Rupert Nash, The University of Edinburgh, CC-BY";
}
epcc.footer_text = footer;

var cpptheme = new Theme(
    (str => str.substring(0, str.lastIndexOf("/")))(import.meta.url),
    '$BASEURL/style.css',
    {
        thumb: function () {
            return '.thumb[\n.thumbtxt[\n' + this +'\n]\n]';
        }
    }
);

epcc.install();
cpptheme.install();
globalThis.slideshow = remark.create({sourceUrl: 'README.md'});
