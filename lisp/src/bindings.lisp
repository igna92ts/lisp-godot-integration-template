(in-package :sim.core)

(sb-alien:define-alien-callable simstart sb-alien:int ()
  (start))

(sb-alien:define-alien-callable simstop sb-alien:void ()
  (stop))
