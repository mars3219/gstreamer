// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst.BaseSharp {

	using System;
	using System.Runtime.InteropServices;

#region Autogenerated code
	[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
	internal delegate int CollectPadsBufferFunctionNative(IntPtr pads, IntPtr data, IntPtr buffer, IntPtr user_data);

	internal class CollectPadsBufferFunctionInvoker {

		CollectPadsBufferFunctionNative native_cb;
		IntPtr __data;
		GLib.DestroyNotify __notify;

		~CollectPadsBufferFunctionInvoker ()
		{
			if (__notify == null)
				return;
			__notify (__data);
		}

		internal CollectPadsBufferFunctionInvoker (CollectPadsBufferFunctionNative native_cb) : this (native_cb, IntPtr.Zero, null) {}

		internal CollectPadsBufferFunctionInvoker (CollectPadsBufferFunctionNative native_cb, IntPtr data) : this (native_cb, data, null) {}

		internal CollectPadsBufferFunctionInvoker (CollectPadsBufferFunctionNative native_cb, IntPtr data, GLib.DestroyNotify notify)
		{
			this.native_cb = native_cb;
			__data = data;
			__notify = notify;
		}

		internal Gst.Base.CollectPadsBufferFunction Handler {
			get {
				return new Gst.Base.CollectPadsBufferFunction(InvokeNative);
			}
		}

		Gst.FlowReturn InvokeNative (Gst.Base.CollectPads pads, Gst.Base.CollectData data, Gst.Buffer buffer)
		{
			IntPtr native_data = GLib.Marshaller.StructureToPtrAlloc (data);
			buffer.Owned = false;
			Gst.FlowReturn __result = (Gst.FlowReturn) native_cb (pads == null ? IntPtr.Zero : pads.Handle, native_data, buffer == null ? IntPtr.Zero : buffer.Handle, __data);
			Marshal.FreeHGlobal (native_data);
			return __result;
		}
	}

	internal class CollectPadsBufferFunctionWrapper {

		public int NativeCallback (IntPtr pads, IntPtr data, IntPtr buffer, IntPtr user_data)
		{
			try {
				Gst.FlowReturn __ret = managed (GLib.Object.GetObject(pads) as Gst.Base.CollectPads, Gst.Base.CollectData.New (data), buffer == IntPtr.Zero ? null : (Gst.Buffer) GLib.Opaque.GetOpaque (buffer, typeof (Gst.Buffer), true));
				if (release_on_call)
					gch.Free ();
				return (int) __ret;
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: Above call does not return.
				throw e;
			}
		}

		bool release_on_call = false;
		GCHandle gch;

		public void PersistUntilCalled ()
		{
			release_on_call = true;
			gch = GCHandle.Alloc (this);
		}

		internal CollectPadsBufferFunctionNative NativeDelegate;
		Gst.Base.CollectPadsBufferFunction managed;

		public CollectPadsBufferFunctionWrapper (Gst.Base.CollectPadsBufferFunction managed)
		{
			this.managed = managed;
			if (managed != null)
				NativeDelegate = new CollectPadsBufferFunctionNative (NativeCallback);
		}

		public static Gst.Base.CollectPadsBufferFunction GetManagedDelegate (CollectPadsBufferFunctionNative native)
		{
			if (native == null)
				return null;
			CollectPadsBufferFunctionWrapper wrapper = (CollectPadsBufferFunctionWrapper) native.Target;
			if (wrapper == null)
				return null;
			return wrapper.managed;
		}
	}
#endregion
}
