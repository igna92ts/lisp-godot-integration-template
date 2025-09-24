using Godot;
using System;
using System.Runtime.InteropServices;

public partial class IpcTest : Node
{
#if GODOT_WINDOWS
    [DllImport("kernel32", SetLastError = true, CharSet = CharSet.Unicode)]
    static extern bool SetDllDirectory(string lpPathName);

    [DllImport("simwrap", CallingConvention = CallingConvention.Cdecl)]
    static extern int sim_init(string corePath);

    [DllImport("simwrap", CallingConvention = CallingConvention.Cdecl)]
    static extern int sim_start_now();

    [DllImport("simwrap", CallingConvention = CallingConvention.Cdecl)]
    static extern void sim_stop_now();
#endif

    public override void _Ready()
    {
        var lispDir = ProjectSettings.GlobalizePath("res://lisp");
        var corePath = ProjectSettings.GlobalizePath("res://lisp/sim.core");

        // make Windows loader look in res://lisp for libsbcl.so dependency
        SetDllDirectory(lispDir);
        System.Environment.SetEnvironmentVariable(
          "PATH",
          lispDir + ";" + System.Environment.GetEnvironmentVariable("PATH")
        );

        var rc = sim_init(corePath);
        if (rc != 0)
        {
            GD.PrintErr($"sim_init failed: {rc} (check sim.core & libsbcl.so in res://lisp)");
            return;
        }

        var s = sim_start_now();
        if (s != 0) GD.PushWarning($"sim_start_now returned {s}");
        else GD.Print("SBCL sim started.");
    }

    public override void _ExitTree()
    {
        try { sim_stop_now(); } catch { }
    }
}
