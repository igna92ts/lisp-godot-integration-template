(in-package :sim.core)

(sb-alien:define-alien-callable ("sim_start" sim-start) sb-alien:int ()
  (start))

(sb-alien:define-alien-callable ("sim_stop"  sim-stop)  sb-alien:void ()
  (stop))
