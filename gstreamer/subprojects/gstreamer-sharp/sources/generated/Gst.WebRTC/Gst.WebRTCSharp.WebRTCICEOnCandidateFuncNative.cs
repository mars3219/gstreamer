// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst.WebRTCSharp {

	using System;
	using System.Runtime.InteropServices;

#region Autogenerated code
	[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
	internal delegate void WebRTCICEOnCandidateFuncNative(IntPtr ice, uint stream_id, IntPtr candidate, IntPtr user_data);

	internal class WebRTCICEOnCandidateFuncInvoker {

		WebRTCICEOnCandidateFuncNative native_cb;
		IntPtr __data;
		GLib.DestroyNotify __notify;

		~WebRTCICEOnCandidateFuncInvoker ()
		{
			if (__notify == null)
				return;
			__notify (__data);
		}

		internal WebRTCICEOnCandidateFuncInvoker (WebRTCICEOnCandidateFuncNative native_cb) : this (native_cb, IntPtr.Zero, null) {}

		internal WebRTCICEOnCandidateFuncInvoker (WebRTCICEOnCandidateFuncNative native_cb, IntPtr data) : this (native_cb, data, null) {}

		internal WebRTCICEOnCandidateFuncInvoker (WebRTCICEOnCandidateFuncNative native_cb, IntPtr data, GLib.DestroyNotify notify)
		{
			this.native_cb = native_cb;
			__data = data;
			__notify = notify;
		}

		internal Gst.WebRTC.WebRTCICEOnCandidateFunc Handler {
			get {
				return new Gst.WebRTC.WebRTCICEOnCandidateFunc(InvokeNative);
			}
		}

		void InvokeNative (Gst.WebRTC.WebRTCICE ice, uint stream_id, string candidate)
		{
			IntPtr native_candidate = GLib.Marshaller.StringToPtrGStrdup (candidate);
			native_cb (ice == null ? IntPtr.Zero : ice.Handle, stream_id, native_candidate, __data);
			GLib.Marshaller.Free (native_candidate);
		}
	}

	internal class WebRTCICEOnCandidateFuncWrapper {

		public void NativeCallback (IntPtr ice, uint stream_id, IntPtr candidate, IntPtr user_data)
		{
			try {
				managed (GLib.Object.GetObject(ice) as Gst.WebRTC.WebRTCICE, stream_id, GLib.Marshaller.Utf8PtrToString (candidate));
				if (release_on_call)
					gch.Free ();
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		bool release_on_call = false;
		GCHandle gch;

		public void PersistUntilCalled ()
		{
			release_on_call = true;
			gch = GCHandle.Alloc (this);
		}

		internal WebRTCICEOnCandidateFuncNative NativeDelegate;
		Gst.WebRTC.WebRTCICEOnCandidateFunc managed;

		public WebRTCICEOnCandidateFuncWrapper (Gst.WebRTC.WebRTCICEOnCandidateFunc managed)
		{
			this.managed = managed;
			if (managed != null)
				NativeDelegate = new WebRTCICEOnCandidateFuncNative (NativeCallback);
		}

		public static Gst.WebRTC.WebRTCICEOnCandidateFunc GetManagedDelegate (WebRTCICEOnCandidateFuncNative native)
		{
			if (native == null)
				return null;
			WebRTCICEOnCandidateFuncWrapper wrapper = (WebRTCICEOnCandidateFuncWrapper) native.Target;
			if (wrapper == null)
				return null;
			return wrapper.managed;
		}
	}
#endregion
}
