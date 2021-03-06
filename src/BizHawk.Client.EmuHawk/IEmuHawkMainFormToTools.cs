using System;
using System.Windows.Forms;

using BizHawk.Bizware.BizwareGL;
using BizHawk.Client.Common;

namespace BizHawk.Client.EmuHawk
{
	public interface IMainFormForTools
	{
		CheatCollection CheatList { get; }

		string CurrentlyOpenRom { get; }

		/// <remarks>only referenced from <see cref="HexEditor"/></remarks>
		LoadRomArgs CurrentlyOpenRomArgs { get; }

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		bool EmulatorPaused { get; }

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		bool GameIsClosing { get; }

		/// <remarks>only referenced from <see cref="PlaybackBox"/></remarks>
		bool HoldFrameAdvance { set; }

		/// <remarks>only referenced from <see cref="BasicBot"/></remarks>
		bool InvisibleEmulation { get; set; }

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		bool IsSeeking { get; }

		/// <remarks>only referenced from <see cref="LuaConsole"/></remarks>
		bool IsTurboing { get; }

		/// <remarks>only referenced from <see cref="PresentationPanel"/></remarks>
		MouseEventHandler MainForm_MouseClick { get; }

		/// <remarks>only referenced from <see cref="PresentationPanel"/></remarks>
		MouseEventHandler MainForm_MouseMove { get; }

		/// <remarks>only referenced from <see cref="PresentationPanel"/></remarks>
		MouseEventHandler MainForm_MouseWheel { get; }

		int? PauseOnFrame { get; set; }

		/// <remarks>only referenced from <see cref="PlaybackBox"/></remarks>
		bool PressRewind { set; }

		/// <remarks>only referenced from <see cref="GenericDebugger"/></remarks>
		event Action<bool> OnPauseChanged;

		void AddOnScreenMessage(string message);

		BitmapBuffer CaptureOSD();

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		void DisableRewind();

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		void EnableRewind(bool enabled);

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		bool EnsureCoreIsAccurate();

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		void FrameAdvance();

		/// <remarks>only referenced from <see cref="LuaConsole"/></remarks>
		void FrameBufferResized();

		/// <remarks>only referenced from <see cref="BasicBot"/></remarks>
		void LoadQuickSave(string quickSlotName, bool suppressOSD = false);

		/// <remarks>only referenced from <see cref="MultiDiskBundler"/></remarks>
		bool LoadRom(string path, LoadRomArgs args);

		/// <remarks>only referenced from <see cref="BookmarksBranchesBox"/></remarks>
		BitmapBuffer MakeScreenshotImage();

		void PauseEmulator();

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		void RelinquishControl(IControlMainform master);

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		void SeekFrameAdvance();

		void SetMainformMovieInfo();

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		void SetWindowText();

		/// <remarks>only referenced from <see cref="VideoWriterChooserForm"/></remarks>
		DialogResult ShowDialogAsChild(Form dialog);

		bool StartNewMovie(IMovie movie, bool record);

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		void TakeBackControl();

		/// <remarks>only referenced from <see cref="BasicBot"/></remarks>
		void Throttle();

		/// <remarks>only referenced from <see cref="PresentationPanel"/></remarks>
		void ToggleFullscreen(bool allowSuppress = false);

		/// <remarks>only referenced from <see cref="TAStudio"/></remarks>
		void TogglePause();

		void UnpauseEmulator();

		/// <remarks>only referenced from <see cref="BasicBot"/></remarks>
		void Unthrottle();

		/// <remarks>only referenced from <see cref="LogWindow"/></remarks>
		void UpdateDumpIcon();

		/// <remarks>only referenced from <see cref="BookmarksBranchesBox"/></remarks>
		void UpdateStatusSlots();
	}
}
