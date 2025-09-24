;;;; build-core-asdf.lisp
(require :asdf)
;; ASDF will find sim-core via ASDF_SOURCE_REGISTRY provided by the Makefile.
(asdf:load-system :sim-core)

(sb-ext:save-lisp-and-die "sim.core"
  :compression t
  :callable-exports '(sim.core:sim-start sim.core:sim-stop))
