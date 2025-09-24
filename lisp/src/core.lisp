(in-package :sim.core)

(defvar *running* nil)

(defun start ()
  (unless *running*
    (setf *running* t)
    (format t "~&[LISP] sim started~%")
    (finish-output))
  0) ; return int success

(defun stop ()
  (when *running*
    (setf *running* nil)
    (format t "~&[LISP] sim stopped~%")
    (finish-output)))
