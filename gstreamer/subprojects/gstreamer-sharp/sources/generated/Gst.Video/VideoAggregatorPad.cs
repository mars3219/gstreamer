// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst.Video {

	using System;
	using System.Collections;
	using System.Collections.Generic;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public partial class VideoAggregatorPad : Gst.Base.AggregatorPad {

		public VideoAggregatorPad (IntPtr raw) : base(raw) {}

		protected VideoAggregatorPad() : base(IntPtr.Zero)
		{
			CreateNativeObject (new string [0], new GLib.Value [0]);
		}

		[GLib.Property ("max-last-buffer-repeat")]
		public ulong MaxLastBufferRepeat {
			get {
				GLib.Value val = GetProperty ("max-last-buffer-repeat");
				ulong ret = (ulong) val;
				val.Dispose ();
				return ret;
			}
			set {
				GLib.Value val = new GLib.Value(value);
				SetProperty("max-last-buffer-repeat", val);
				val.Dispose ();
			}
		}

		[GLib.Property ("repeat-after-eos")]
		public bool RepeatAfterEos {
			get {
				GLib.Value val = GetProperty ("repeat-after-eos");
				bool ret = (bool) val;
				val.Dispose ();
				return ret;
			}
			set {
				GLib.Value val = new GLib.Value(value);
				SetProperty("repeat-after-eos", val);
				val.Dispose ();
			}
		}

		[GLib.Property ("zorder")]
		public uint Zorder {
			get {
				GLib.Value val = GetProperty ("zorder");
				uint ret = (uint) val;
				val.Dispose ();
				return ret;
			}
			set {
				GLib.Value val = new GLib.Value(value);
				SetProperty("zorder", val);
				val.Dispose ();
			}
		}

		public Gst.Video.VideoInfo Info {
			get {
				unsafe {
					IntPtr* raw_ptr = (IntPtr*)(((byte*)Handle) + abi_info.GetFieldOffset("info"));
					return (*raw_ptr) == IntPtr.Zero ? null : (Gst.Video.VideoInfo) GLib.Opaque.GetOpaque ((*raw_ptr), typeof (Gst.Video.VideoInfo), false);
				}
			}
		}

		static UpdateConversionInfoNativeDelegate UpdateConversionInfo_cb_delegate;
		static UpdateConversionInfoNativeDelegate UpdateConversionInfoVMCallback {
			get {
				if (UpdateConversionInfo_cb_delegate == null)
					UpdateConversionInfo_cb_delegate = new UpdateConversionInfoNativeDelegate (UpdateConversionInfo_cb);
				return UpdateConversionInfo_cb_delegate;
			}
		}

		static void OverrideUpdateConversionInfo (GLib.GType gtype)
		{
			OverrideUpdateConversionInfo (gtype, UpdateConversionInfoVMCallback);
		}

		static void OverrideUpdateConversionInfo (GLib.GType gtype, UpdateConversionInfoNativeDelegate callback)
		{
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) gtype.GetClassPtr()) + (long) class_abi.GetFieldOffset("update_conversion_info"));
				*raw_ptr = Marshal.GetFunctionPointerForDelegate((Delegate) callback);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void UpdateConversionInfoNativeDelegate (IntPtr inst);

		static void UpdateConversionInfo_cb (IntPtr inst)
		{
			try {
				VideoAggregatorPad __obj = GLib.Object.GetObject (inst, false) as VideoAggregatorPad;
				__obj.OnUpdateConversionInfo ();
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[GLib.DefaultSignalHandler(Type=typeof(Gst.Video.VideoAggregatorPad), ConnectionMethod="OverrideUpdateConversionInfo")]
		protected virtual void OnUpdateConversionInfo ()
		{
			InternalUpdateConversionInfo ();
		}

		private void InternalUpdateConversionInfo ()
		{
			UpdateConversionInfoNativeDelegate unmanaged = null;
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) this.LookupGType().GetThresholdType().GetClassPtr()) + (long) class_abi.GetFieldOffset("update_conversion_info"));
				unmanaged = (UpdateConversionInfoNativeDelegate) Marshal.GetDelegateForFunctionPointer(*raw_ptr, typeof(UpdateConversionInfoNativeDelegate));
			}
			if (unmanaged == null) return;

			unmanaged (this.Handle);
		}

		static PrepareFrameNativeDelegate PrepareFrame_cb_delegate;
		static PrepareFrameNativeDelegate PrepareFrameVMCallback {
			get {
				if (PrepareFrame_cb_delegate == null)
					PrepareFrame_cb_delegate = new PrepareFrameNativeDelegate (PrepareFrame_cb);
				return PrepareFrame_cb_delegate;
			}
		}

		static void OverridePrepareFrame (GLib.GType gtype)
		{
			OverridePrepareFrame (gtype, PrepareFrameVMCallback);
		}

		static void OverridePrepareFrame (GLib.GType gtype, PrepareFrameNativeDelegate callback)
		{
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) gtype.GetClassPtr()) + (long) class_abi.GetFieldOffset("prepare_frame"));
				*raw_ptr = Marshal.GetFunctionPointerForDelegate((Delegate) callback);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool PrepareFrameNativeDelegate (IntPtr inst, IntPtr videoaggregator, IntPtr buffer, IntPtr prepared_frame);

		static bool PrepareFrame_cb (IntPtr inst, IntPtr videoaggregator, IntPtr buffer, IntPtr prepared_frame)
		{
			try {
				VideoAggregatorPad __obj = GLib.Object.GetObject (inst, false) as VideoAggregatorPad;
				bool __result;
				__result = __obj.OnPrepareFrame (GLib.Object.GetObject(videoaggregator) as Gst.Video.VideoAggregator, buffer == IntPtr.Zero ? null : (Gst.Buffer) GLib.Opaque.GetOpaque (buffer, typeof (Gst.Buffer), false), Gst.Video.VideoFrame.New (prepared_frame));
				return __result;
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[GLib.DefaultSignalHandler(Type=typeof(Gst.Video.VideoAggregatorPad), ConnectionMethod="OverridePrepareFrame")]
		protected virtual bool OnPrepareFrame (Gst.Video.VideoAggregator videoaggregator, Gst.Buffer buffer, Gst.Video.VideoFrame prepared_frame)
		{
			return InternalPrepareFrame (videoaggregator, buffer, prepared_frame);
		}

		private bool InternalPrepareFrame (Gst.Video.VideoAggregator videoaggregator, Gst.Buffer buffer, Gst.Video.VideoFrame prepared_frame)
		{
			PrepareFrameNativeDelegate unmanaged = null;
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) this.LookupGType().GetThresholdType().GetClassPtr()) + (long) class_abi.GetFieldOffset("prepare_frame"));
				unmanaged = (PrepareFrameNativeDelegate) Marshal.GetDelegateForFunctionPointer(*raw_ptr, typeof(PrepareFrameNativeDelegate));
			}
			if (unmanaged == null) return false;

			IntPtr native_prepared_frame = GLib.Marshaller.StructureToPtrAlloc (prepared_frame);
			bool __result = unmanaged (this.Handle, videoaggregator == null ? IntPtr.Zero : videoaggregator.Handle, buffer == null ? IntPtr.Zero : buffer.Handle, native_prepared_frame);
			Marshal.FreeHGlobal (native_prepared_frame);
			return __result;
		}

		static CleanFrameNativeDelegate CleanFrame_cb_delegate;
		static CleanFrameNativeDelegate CleanFrameVMCallback {
			get {
				if (CleanFrame_cb_delegate == null)
					CleanFrame_cb_delegate = new CleanFrameNativeDelegate (CleanFrame_cb);
				return CleanFrame_cb_delegate;
			}
		}

		static void OverrideCleanFrame (GLib.GType gtype)
		{
			OverrideCleanFrame (gtype, CleanFrameVMCallback);
		}

		static void OverrideCleanFrame (GLib.GType gtype, CleanFrameNativeDelegate callback)
		{
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) gtype.GetClassPtr()) + (long) class_abi.GetFieldOffset("clean_frame"));
				*raw_ptr = Marshal.GetFunctionPointerForDelegate((Delegate) callback);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void CleanFrameNativeDelegate (IntPtr inst, IntPtr videoaggregator, IntPtr prepared_frame);

		static void CleanFrame_cb (IntPtr inst, IntPtr videoaggregator, IntPtr prepared_frame)
		{
			try {
				VideoAggregatorPad __obj = GLib.Object.GetObject (inst, false) as VideoAggregatorPad;
				__obj.OnCleanFrame (GLib.Object.GetObject(videoaggregator) as Gst.Video.VideoAggregator, Gst.Video.VideoFrame.New (prepared_frame));
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[GLib.DefaultSignalHandler(Type=typeof(Gst.Video.VideoAggregatorPad), ConnectionMethod="OverrideCleanFrame")]
		protected virtual void OnCleanFrame (Gst.Video.VideoAggregator videoaggregator, Gst.Video.VideoFrame prepared_frame)
		{
			InternalCleanFrame (videoaggregator, prepared_frame);
		}

		private void InternalCleanFrame (Gst.Video.VideoAggregator videoaggregator, Gst.Video.VideoFrame prepared_frame)
		{
			CleanFrameNativeDelegate unmanaged = null;
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) this.LookupGType().GetThresholdType().GetClassPtr()) + (long) class_abi.GetFieldOffset("clean_frame"));
				unmanaged = (CleanFrameNativeDelegate) Marshal.GetDelegateForFunctionPointer(*raw_ptr, typeof(CleanFrameNativeDelegate));
			}
			if (unmanaged == null) return;

			IntPtr native_prepared_frame = GLib.Marshaller.StructureToPtrAlloc (prepared_frame);
			unmanaged (this.Handle, videoaggregator == null ? IntPtr.Zero : videoaggregator.Handle, native_prepared_frame);
			Marshal.FreeHGlobal (native_prepared_frame);
		}

		static PrepareFrameStartNativeDelegate PrepareFrameStart_cb_delegate;
		static PrepareFrameStartNativeDelegate PrepareFrameStartVMCallback {
			get {
				if (PrepareFrameStart_cb_delegate == null)
					PrepareFrameStart_cb_delegate = new PrepareFrameStartNativeDelegate (PrepareFrameStart_cb);
				return PrepareFrameStart_cb_delegate;
			}
		}

		static void OverridePrepareFrameStart (GLib.GType gtype)
		{
			OverridePrepareFrameStart (gtype, PrepareFrameStartVMCallback);
		}

		static void OverridePrepareFrameStart (GLib.GType gtype, PrepareFrameStartNativeDelegate callback)
		{
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) gtype.GetClassPtr()) + (long) class_abi.GetFieldOffset("prepare_frame_start"));
				*raw_ptr = Marshal.GetFunctionPointerForDelegate((Delegate) callback);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void PrepareFrameStartNativeDelegate (IntPtr inst, IntPtr videoaggregator, IntPtr buffer, IntPtr prepared_frame);

		static void PrepareFrameStart_cb (IntPtr inst, IntPtr videoaggregator, IntPtr buffer, IntPtr prepared_frame)
		{
			try {
				VideoAggregatorPad __obj = GLib.Object.GetObject (inst, false) as VideoAggregatorPad;
				__obj.OnPrepareFrameStart (GLib.Object.GetObject(videoaggregator) as Gst.Video.VideoAggregator, buffer == IntPtr.Zero ? null : (Gst.Buffer) GLib.Opaque.GetOpaque (buffer, typeof (Gst.Buffer), false), Gst.Video.VideoFrame.New (prepared_frame));
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[GLib.DefaultSignalHandler(Type=typeof(Gst.Video.VideoAggregatorPad), ConnectionMethod="OverridePrepareFrameStart")]
		protected virtual void OnPrepareFrameStart (Gst.Video.VideoAggregator videoaggregator, Gst.Buffer buffer, Gst.Video.VideoFrame prepared_frame)
		{
			InternalPrepareFrameStart (videoaggregator, buffer, prepared_frame);
		}

		private void InternalPrepareFrameStart (Gst.Video.VideoAggregator videoaggregator, Gst.Buffer buffer, Gst.Video.VideoFrame prepared_frame)
		{
			PrepareFrameStartNativeDelegate unmanaged = null;
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) this.LookupGType().GetThresholdType().GetClassPtr()) + (long) class_abi.GetFieldOffset("prepare_frame_start"));
				unmanaged = (PrepareFrameStartNativeDelegate) Marshal.GetDelegateForFunctionPointer(*raw_ptr, typeof(PrepareFrameStartNativeDelegate));
			}
			if (unmanaged == null) return;

			IntPtr native_prepared_frame = GLib.Marshaller.StructureToPtrAlloc (prepared_frame);
			unmanaged (this.Handle, videoaggregator == null ? IntPtr.Zero : videoaggregator.Handle, buffer == null ? IntPtr.Zero : buffer.Handle, native_prepared_frame);
			Marshal.FreeHGlobal (native_prepared_frame);
		}

		static PrepareFrameFinishNativeDelegate PrepareFrameFinish_cb_delegate;
		static PrepareFrameFinishNativeDelegate PrepareFrameFinishVMCallback {
			get {
				if (PrepareFrameFinish_cb_delegate == null)
					PrepareFrameFinish_cb_delegate = new PrepareFrameFinishNativeDelegate (PrepareFrameFinish_cb);
				return PrepareFrameFinish_cb_delegate;
			}
		}

		static void OverridePrepareFrameFinish (GLib.GType gtype)
		{
			OverridePrepareFrameFinish (gtype, PrepareFrameFinishVMCallback);
		}

		static void OverridePrepareFrameFinish (GLib.GType gtype, PrepareFrameFinishNativeDelegate callback)
		{
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) gtype.GetClassPtr()) + (long) class_abi.GetFieldOffset("prepare_frame_finish"));
				*raw_ptr = Marshal.GetFunctionPointerForDelegate((Delegate) callback);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void PrepareFrameFinishNativeDelegate (IntPtr inst, IntPtr videoaggregator, IntPtr prepared_frame);

		static void PrepareFrameFinish_cb (IntPtr inst, IntPtr videoaggregator, IntPtr prepared_frame)
		{
			try {
				VideoAggregatorPad __obj = GLib.Object.GetObject (inst, false) as VideoAggregatorPad;
				__obj.OnPrepareFrameFinish (GLib.Object.GetObject(videoaggregator) as Gst.Video.VideoAggregator, Gst.Video.VideoFrame.New (prepared_frame));
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[GLib.DefaultSignalHandler(Type=typeof(Gst.Video.VideoAggregatorPad), ConnectionMethod="OverridePrepareFrameFinish")]
		protected virtual void OnPrepareFrameFinish (Gst.Video.VideoAggregator videoaggregator, Gst.Video.VideoFrame prepared_frame)
		{
			InternalPrepareFrameFinish (videoaggregator, prepared_frame);
		}

		private void InternalPrepareFrameFinish (Gst.Video.VideoAggregator videoaggregator, Gst.Video.VideoFrame prepared_frame)
		{
			PrepareFrameFinishNativeDelegate unmanaged = null;
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) this.LookupGType().GetThresholdType().GetClassPtr()) + (long) class_abi.GetFieldOffset("prepare_frame_finish"));
				unmanaged = (PrepareFrameFinishNativeDelegate) Marshal.GetDelegateForFunctionPointer(*raw_ptr, typeof(PrepareFrameFinishNativeDelegate));
			}
			if (unmanaged == null) return;

			IntPtr native_prepared_frame = GLib.Marshaller.StructureToPtrAlloc (prepared_frame);
			unmanaged (this.Handle, videoaggregator == null ? IntPtr.Zero : videoaggregator.Handle, native_prepared_frame);
			Marshal.FreeHGlobal (native_prepared_frame);
		}


		// Internal representation of the wrapped structure ABI.
		static GLib.AbiStruct _class_abi = null;
		static public new GLib.AbiStruct class_abi {
			get {
				if (_class_abi == null)
					_class_abi = new GLib.AbiStruct (new List<GLib.AbiField>{ 
						new GLib.AbiField("update_conversion_info"
							, Gst.Base.AggregatorPad.class_abi.Fields
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // update_conversion_info
							, null
							, "prepare_frame"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("prepare_frame"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // prepare_frame
							, "update_conversion_info"
							, "clean_frame"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("clean_frame"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // clean_frame
							, "prepare_frame"
							, "prepare_frame_start"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("prepare_frame_start"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // prepare_frame_start
							, "clean_frame"
							, "prepare_frame_finish"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("prepare_frame_finish"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // prepare_frame_finish
							, "prepare_frame_start"
							, "_gst_reserved"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("_gst_reserved"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) * 18 // _gst_reserved
							, "prepare_frame_finish"
							, null
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
					});

				return _class_abi;
			}
		}


		// End of the ABI representation.

		[DllImport("gstvideo-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_video_aggregator_pad_get_type();

		public static new GLib.GType GType { 
			get {
				IntPtr raw_ret = gst_video_aggregator_pad_get_type();
				GLib.GType ret = new GLib.GType(raw_ret);
				return ret;
			}
		}

		[DllImport("gstvideo-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_video_aggregator_pad_get_current_buffer(IntPtr raw);

		public Gst.Buffer CurrentBuffer { 
			get {
				IntPtr raw_ret = gst_video_aggregator_pad_get_current_buffer(Handle);
				Gst.Buffer ret = raw_ret == IntPtr.Zero ? null : (Gst.Buffer) GLib.Opaque.GetOpaque (raw_ret, typeof (Gst.Buffer), false);
				return ret;
			}
		}

		[DllImport("gstvideo-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_video_aggregator_pad_get_prepared_frame(IntPtr raw);

		public Gst.Video.VideoFrame PreparedFrame { 
			get {
				IntPtr raw_ret = gst_video_aggregator_pad_get_prepared_frame(Handle);
				Gst.Video.VideoFrame ret = Gst.Video.VideoFrame.New (raw_ret);
				return ret;
			}
		}

		[DllImport("gstvideo-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_video_aggregator_pad_has_current_buffer(IntPtr raw);

		public bool HasCurrentBuffer { 
			get {
				bool raw_ret = gst_video_aggregator_pad_has_current_buffer(Handle);
				bool ret = raw_ret;
				return ret;
			}
		}

		[DllImport("gstvideo-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_video_aggregator_pad_set_needs_alpha(IntPtr raw, bool needs_alpha);

		public bool NeedsAlpha { 
			set {
				gst_video_aggregator_pad_set_needs_alpha(Handle, value);
			}
		}


		static VideoAggregatorPad ()
		{
			GtkSharp.GstreamerSharp.ObjectManager.Initialize ();
		}

		// Internal representation of the wrapped structure ABI.
		static GLib.AbiStruct _abi_info = null;
		static public new GLib.AbiStruct abi_info {
			get {
				if (_abi_info == null)
					_abi_info = new GLib.AbiStruct (new List<GLib.AbiField>{ 
						new GLib.AbiField("info"
							, Gst.Base.AggregatorPad.abi_info.Fields
							, Gst.Video.VideoInfo.abi_info.Size // info
							, null
							, "priv"
							, Gst.Video.VideoInfo.abi_info.Align
							, 0
							),
						new GLib.AbiField("priv"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // priv
							, "info"
							, "_gst_reserved"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("_gst_reserved"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) * 4 // _gst_reserved
							, "priv"
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
