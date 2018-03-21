(TeX-add-style-hook
 "preamble"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("scrbook" "a4paper" "BCOR1.0cm")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("fontenc" "T1") ("hyperref" "extension=pdf")))
   (TeX-run-style-hooks
    "latex2e"
    "htmlpreamble"
    "mutaborlst"
    "scrbook"
    "scrbook10"
    "inputenc"
    "fontenc"
    "babel"
    "etoolbox"
    "amsmath"
    "xr-hyper"
    "hyperref"
    "nameref"
    "graphicx"
    "tikz"
    "listings"
    "tsemlines"
    "makeidx"
    "keystroke")
   (TeX-add-symbols
    '("translate" 1)
    '("mutimage" 2)
    '("cdoronline" 2)
    '("keyword" 1)
    '("tsreflink" 2)
    '("helpsection" 2)
    '("vollref" 1)
    '("tsciteref" 1)
    '("makefilename" 1)
    "outputformat"
    "ts"
    "reflink"
    "sourcecode"
    "filename"
    "textat"
    "textapostrophe"
    "addchapname"
    "likesectionname"))
 :latex)

