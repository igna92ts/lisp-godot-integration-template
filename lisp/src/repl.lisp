(in-package :sim.core)

(defun start-swank-repl (&key (port 4005))
  "Start Swank REPL on the given port in a separate thread."
  (swank:create-server :port port :dont-close t)
  0)

