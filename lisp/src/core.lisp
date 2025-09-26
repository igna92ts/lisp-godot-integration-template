(in-package :sim.core)

(defvar *running* nil)

(defun start ()
  (unless *running*
    (setf *running* t))
  0)

(defun stop ()
  (when *running*
    (setf *running* nil)))
