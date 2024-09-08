// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst.RtspServer {

	using System;
	using System.Collections;
	using System.Collections.Generic;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public partial class RTSPOnvifClient : Gst.RtspServer.RTSPClient {

		public RTSPOnvifClient (IntPtr raw) : base(raw) {}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_rtsp_onvif_client_new();

		public RTSPOnvifClient () : base (IntPtr.Zero)
		{
			if (GetType () != typeof (RTSPOnvifClient)) {
				CreateNativeObject (new string [0], new GLib.Value[0]);
				return;
			}
			Raw = gst_rtsp_onvif_client_new();
		}


		// Internal representation of the wrapped structure ABI.
		static GLib.AbiStruct _class_abi = null;
		static public new GLib.AbiStruct class_abi {
			get {
				if (_class_abi == null)
					_class_abi = new GLib.AbiStruct (new List<GLib.AbiField>{ 
						new GLib.AbiField("_gst_reserved"
							, Gst.RtspServer.RTSPClient.class_abi.Fields
							, (uint) Marshal.SizeOf(typeof(IntPtr)) * 20 // _gst_reserved
							, null
							, null
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
					});

				return _class_abi;
			}
		}


		// End of the ABI representation.

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_rtsp_onvif_client_get_type();

		public static new GLib.GType GType { 
			get {
				IntPtr raw_ret = gst_rtsp_onvif_client_get_type();
				GLib.GType ret = new GLib.GType(raw_ret);
				return ret;
			}
		}


		static RTSPOnvifClient ()
		{
			GtkSharp.GstreamerSharp.ObjectManager.Initialize ();
		}

		// Internal representation of the wrapped structure ABI.
		static GLib.AbiStruct _abi_info = null;
		static public new GLib.AbiStruct abi_info {
			get {
				if (_abi_info == null)
					_abi_info = new GLib.AbiStruct (new List<GLib.AbiField>{ 
						new GLib.AbiField("_gst_reserved"
							, Gst.RtspServer.RTSPClient.abi_info.Fields
							, (uint) Marshal.SizeOf(typeof(IntPtr)) * 4 // _gst_reserved
							, null
							, null
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
					});

				return _abi_info;
			}
		}


		// End of the ABI representation.

#endregion
	}
}
