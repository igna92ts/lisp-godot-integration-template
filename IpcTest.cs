using Godot;
using System;
using System.Runtime.InteropServices;

public partial class IpcTest : Node
{
    [DllImport("kernel32", SetLastError = true, CharSet = CharSet.Ansi)]
    static extern bool SetDllDirectoryA(string lpPathName);

    [DllImport("simwrap.dll", EntryPoint = "init_sim")]
    static extern int init_sim();

    [DllImport("simwrap.dll", EntryPoint = "start_simulation")]
    static extern int start_simulation();

    [DllImport("simwrap.dll", EntryPoint = "stop_simulation")]
    static extern void stop_simulation();

    public override void _Ready()
    {
        var lispDir = ProjectSettings.GlobalizePath("res://lisp");
        GD.Print($"[SimBridge] Lisp dir: {lispDir}");
        // Ensure loader can find simwrap.dll and its deps
        if (!SetDllDirectoryA(lispDir))
            GD.PushWarning("SetDllDirectoryA failed. DLLs must be in executable folder or PATH.");

        GD.Print($"[SimBridge] core path: {ProjectSettings.GlobalizePath("res://lisp/sim.core")}");
        try
        {
            int rc = init_sim();
            if (rc != 0) { GD.PushError($"init_sim failed: {rc}"); GetTree().Quit(1); return; }
            GD.Print("[SimBridge] init_sim ok");
            var res = start_simulation();
            GD.Print($"simulation started -> {res}");
        }
        catch (DllNotFoundException dnfe)
        {
            GD.PushError("DllNotFoundException: " + dnfe.Message);
            GetTree().Quit(2);
        }
        catch (BadImageFormatException bif)
        {
            GD.PushError("BadImageFormatException (arch mismatch): " + bif.Message);
            GetTree().Quit(3);
        }
        catch (Exception ex)
        {
            GD.PushError("init_sim exception: " + ex.ToString());
            GetTree().Quit(4);
        }
    }

    public override void _ExitTree()
    {
        try { stop_simulation(); } catch { }
    }
}

