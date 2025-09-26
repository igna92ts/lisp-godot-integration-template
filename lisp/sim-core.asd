(asdf:defsystem "sim-core"
  :serial t
  :depends-on ("swank")
  :components ((:file "src/package")
               (:file "src/core")
               (:file "src/bindings")
               (:file "src/repl")))
