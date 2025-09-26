(require :asdf)
(asdf:load-system :sim-core)
(in-package :sim.core)

(sb-ext:save-lisp-and-die "sim.core"
  :executable nil
  :compression t
  :callable-exports (list 'simstart 'simstop 'start-repl))
