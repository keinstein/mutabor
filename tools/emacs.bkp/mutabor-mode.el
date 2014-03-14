;;; mutabor-mode.el --- Frobnicate and bifurcate flanges
     
;; Copyright (C) 2014 Tobias Schlemmer
     
;; Author:  Tobias Schlemmer <keinstein@users.sourceforge.net>
;; Version: 0.1
;; Keywords: files, languages, multimedia
     
;;; Commentary:
     
;; This package provides a major mode for the MUTABOR tuning
;; language. It is designated to users who wish to edit their dynamic
;; musical tunigs with another editor than the one built into MUTABOR.
;; For further information see: http://www.math.tu-dresden.de/~mutabor/


;;; Code:
(defvar mutabor-mode-hook nil)

(defvar mutabor-mode-map
  (let ((map (make-keymap)))
    (define-key map "\C-j" 'newline-and-indent)
    map)
  "Keymap for MUTABOR major mode")

;;;###autoload
(add-to-list 'auto-mode-alist '("\\.mut\\'" . mutabor-mode))



;; MUTABOR language keyword definitions
;; this list could be optimized using a call like 
;; (regexp-opt '("PARTICIPANT" "END_PARTICIPANT" "MODEL" "END_MODEL"
;; "WORKFLOW" "END_WORKFLOW" "ACTIVITY" "END_ACTIVITY" "TRANSITION"
;; "END_TRANSITION" "APPLICATION" "END_APPLICATION" "DATA" "END_DATA"
;; "TOOL_LIST" "END_TOOL_LIST") t)
(defconst mutabor-font-lock-keywords-1
  (list
   ;;   '("\\<\\(A\\(CTIVITY\\|PPLICATION\\)\\|DATA\\|END_\\(A\\(CTIVITY\\|PPLICATION\\)\\|DATA\\|MODEL\\|PARTICIPANT\\|T\\(OOL_LIST\\|RANSITION\\)\\|WORKFLOW\\)\\|MODEL\\|PARTICIPANT\\|T\\(OOL_LIST\\|RANSITION\\)\\|WORKFLOW\\)\\>" . font-lock-builtin-face)
   '("\\<\\(INTERVALL?\\|TONE?\\(SYSTEM\\)?\\|UMSTIMMUNG\\|RETUNING\\|HARMON\\(Y\\|IE\\)\\|MIDIKANAL\\|INSTRUMENT\\)\\>" . font-lock-builtin-face)
   '("\\('\\w*'\\)" . font-lock-variable-name-face))
  "Minimal highlighting expressions for MUTABOR mode")

;; second level keywords including the above ones
(defconst mutabor-font-lock-keywords-2
  (append mutabor-font-lock-keywords-1
	  (list
	   '("\\<\\(HARMONIEANALYSE\\|HARMONY_ANALYSIS\\|TASTE\\|KEY\\|MIDIIN\\|MIDI EIN\\|MIDIOUT\\|MIDI AUS\\|ANSONSTEN\\|ELSE\\)\\>" . font-lock-keyword-face)
	   '("\\<\\(ZENTRUM\\|CENTER\\|ABSTAND\\|DISTANCE\\)\\>" . font-lock-constant-face)))
  "Additional Keywords to highlight in MUTABOR mode")

(defconst mutabor-font-lock-keywords-3
  (append mutabor-font-lock-keywords-2
	  (list
	   '("\\<\\(WURZEL\\|ROOT\\)\\>" . font-lock-constant-face)))
  "Balls-out highlighting in MUTABOR mode")

(defvar mutabor-font-lock-keywords mutabor-font-lock-keywords-3
  "Default highlighting expressions for MUTABOR mode")

(defun mutabor-indent-line ()
  "Indent current line as MUTABOR code"
  (interactive)
  (beginning-of-line)

  (if (bobp)  ; Check for rule 1
      (indent-line-to 0)
    
    (let ((not-indented t) cur-indent)
      (if (looking-at "^[ \t]*\\(INTERVALL?\\|TONE?\\(SYSTEM\\)?\\|UMSTIMMUNG\\|RETUNING\\|HARMON\\(Y\\|IE\\)\\|MIDIKANAL\\|INSTRUMENT\\)") ; Check for rule 2
;		(setq cur-indent nil)
 	  (progn
 	    (save-excursion
 	      (forward-line -1)
 	      (setq cur-indent (- (current-indentation) tab-width)))
 
 
 	    (if (< cur-indent 0)
 		(setq cur-indent 0))
	    (setq not-indented nil))
	
	(save-excursion 
          (while not-indented
            (forward-line -1)
;            (if (looking-at "^[ \t]*END_") ; Check for rule 3
;                (progn
;                  (setq cur-indent (current-indentation))
;                  (setq not-indented nil))
					; Check for rule 4
              (if (looking-at "^[ \t]*\\(INTERVALL?\\|TONE?\\(SYSTEM\\)?\\|UMSTIMMUNG\\|RETUNING\\|HARMON\\(Y\\|IE\\)\\|MIDIKANAL\\|INSTRUMENT\\)")
                  (progn
                    (setq cur-indent (+ (current-indentation) tab-width))
                    (setq not-indented nil))
                (if (bobp) ; Check for rule 5
                    (setq not-indented nil))))));)   
      (if cur-indent
	  (indent-line-to cur-indent)
	(indent-line-to 0))))) ; If we didn't see an indentation hint, then allow no indentation

; construct a syntax table
(defvar mutabor-mode-syntax-table
  (let ((st (make-syntax-table)))
; the following changes some character classes see the Emacs lisp programming guide for more details
; declare underscores to be a word character
;    (modify-syntax-entry ?_ "w" st)
; c++ style comments
;   (modify-syntax-entry ?/ ". 124b" st)
;    (modify-syntax-entry ?* ". 23" st)
;    (modify-syntax-entry ?\n "> b" st)

; we use the simpler definitions:
   (modify-syntax-entry ?/ "." st)
   (modify-syntax-entry ?* "." st)
   (modify-syntax-entry ?\n ">" st)
   st)
  "Syntax table for mutabor-mode")



(defun mutabor-mode ()
  "Major mode for editing MUTABOR (dynamic) tuning description files"
  (interactive)
  (kill-all-local-variables)
  (set-syntax-table mutabor-mode-syntax-table)
  (use-local-map mutabor-mode-map)
  (set (make-local-variable 'font-lock-defaults) '(mutabor-font-lock-keywords))
  (set (make-local-variable 'indent-line-function) 'mutabor-indent-line)  
  (setq major-mode 'mutabor-mode)
  (setq mode-name "MUTABOR")
  (run-hooks 'mutabor-mode-hook))

(provide 'mutabor-mode)

;;; mutabor-mode.el ends here
