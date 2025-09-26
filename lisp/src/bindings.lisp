(in-package :sim.core)

(sb-alien:define-alien-callable simstart sb-alien:int ()
  (start))

(sb-alien:define-alien-callable simstop sb-alien:void ()
  (stop))

(sb-alien:define-alien-callable start-repl sb-alien:int ((port sb-alien:int))
  (start-swank-repl  :port port))
