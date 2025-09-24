(asdf:defsystem "sim-core"
  :defsystem-depends-on (#:sbcl-librarian)
  :depends-on (#:sbcl-librarian)
  :serial t
  :components ((:file "src/package")
               (:file "src/core")
               (:file "src/bindings")))
