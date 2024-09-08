// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace Gst.RtspServer {

	using System;
	using System.Collections;
	using System.Collections.Generic;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public partial class RTSPAuth : GLib.Object {

		public RTSPAuth (IntPtr raw) : base(raw) {}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_rtsp_auth_new();

		public RTSPAuth () : base (IntPtr.Zero)
		{
			if (GetType () != typeof (RTSPAuth)) {
				CreateNativeObject (new string [0], new GLib.Value[0]);
				return;
			}
			Raw = gst_rtsp_auth_new();
		}

		[GLib.Signal("accept-certificate")]
		public event Gst.RtspServer.AcceptCertificateHandler AcceptCertificate {
			add {
				this.AddSignalHandler ("accept-certificate", value, typeof (Gst.RtspServer.AcceptCertificateArgs));
			}
			remove {
				this.RemoveSignalHandler ("accept-certificate", value);
			}
		}

		static AuthenticateNativeDelegate Authenticate_cb_delegate;
		static AuthenticateNativeDelegate AuthenticateVMCallback {
			get {
				if (Authenticate_cb_delegate == null)
					Authenticate_cb_delegate = new AuthenticateNativeDelegate (Authenticate_cb);
				return Authenticate_cb_delegate;
			}
		}

		static void OverrideAuthenticate (GLib.GType gtype)
		{
			OverrideAuthenticate (gtype, AuthenticateVMCallback);
		}

		static void OverrideAuthenticate (GLib.GType gtype, AuthenticateNativeDelegate callback)
		{
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) gtype.GetClassPtr()) + (long) class_abi.GetFieldOffset("authenticate"));
				*raw_ptr = Marshal.GetFunctionPointerForDelegate((Delegate) callback);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool AuthenticateNativeDelegate (IntPtr inst, IntPtr ctx);

		static bool Authenticate_cb (IntPtr inst, IntPtr ctx)
		{
			try {
				RTSPAuth __obj = GLib.Object.GetObject (inst, false) as RTSPAuth;
				bool __result;
				__result = __obj.OnAuthenticate (Gst.RtspServer.RTSPContext.New (ctx));
				return __result;
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[GLib.DefaultSignalHandler(Type=typeof(Gst.RtspServer.RTSPAuth), ConnectionMethod="OverrideAuthenticate")]
		protected virtual bool OnAuthenticate (Gst.RtspServer.RTSPContext ctx)
		{
			return InternalAuthenticate (ctx);
		}

		private bool InternalAuthenticate (Gst.RtspServer.RTSPContext ctx)
		{
			AuthenticateNativeDelegate unmanaged = null;
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) this.LookupGType().GetThresholdType().GetClassPtr()) + (long) class_abi.GetFieldOffset("authenticate"));
				unmanaged = (AuthenticateNativeDelegate) Marshal.GetDelegateForFunctionPointer(*raw_ptr, typeof(AuthenticateNativeDelegate));
			}
			if (unmanaged == null) return false;

			IntPtr native_ctx = GLib.Marshaller.StructureToPtrAlloc (ctx);
			bool __result = unmanaged (this.Handle, native_ctx);
			Marshal.FreeHGlobal (native_ctx);
			return __result;
		}

		static CheckNativeDelegate Check_cb_delegate;
		static CheckNativeDelegate CheckVMCallback {
			get {
				if (Check_cb_delegate == null)
					Check_cb_delegate = new CheckNativeDelegate (Check_cb);
				return Check_cb_delegate;
			}
		}

		static void OverrideCheck (GLib.GType gtype)
		{
			OverrideCheck (gtype, CheckVMCallback);
		}

		static void OverrideCheck (GLib.GType gtype, CheckNativeDelegate callback)
		{
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) gtype.GetClassPtr()) + (long) class_abi.GetFieldOffset("check"));
				*raw_ptr = Marshal.GetFunctionPointerForDelegate((Delegate) callback);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool CheckNativeDelegate (IntPtr inst, IntPtr ctx, IntPtr check);

		static bool Check_cb (IntPtr inst, IntPtr ctx, IntPtr check)
		{
			try {
				RTSPAuth __obj = GLib.Object.GetObject (inst, false) as RTSPAuth;
				bool __result;
				__result = __obj.OnCheck (Gst.RtspServer.RTSPContext.New (ctx), GLib.Marshaller.Utf8PtrToString (check));
				return __result;
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[GLib.DefaultSignalHandler(Type=typeof(Gst.RtspServer.RTSPAuth), ConnectionMethod="OverrideCheck")]
		protected virtual bool OnCheck (Gst.RtspServer.RTSPContext ctx, string check)
		{
			return InternalCheck (ctx, check);
		}

		private bool InternalCheck (Gst.RtspServer.RTSPContext ctx, string check)
		{
			CheckNativeDelegate unmanaged = null;
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) this.LookupGType().GetThresholdType().GetClassPtr()) + (long) class_abi.GetFieldOffset("check"));
				unmanaged = (CheckNativeDelegate) Marshal.GetDelegateForFunctionPointer(*raw_ptr, typeof(CheckNativeDelegate));
			}
			if (unmanaged == null) return false;

			IntPtr native_ctx = GLib.Marshaller.StructureToPtrAlloc (ctx);
			IntPtr native_check = GLib.Marshaller.StringToPtrGStrdup (check);
			bool __result = unmanaged (this.Handle, native_ctx, native_check);
			Marshal.FreeHGlobal (native_ctx);
			GLib.Marshaller.Free (native_check);
			return __result;
		}

		static GenerateAuthenticateHeaderNativeDelegate GenerateAuthenticateHeader_cb_delegate;
		static GenerateAuthenticateHeaderNativeDelegate GenerateAuthenticateHeaderVMCallback {
			get {
				if (GenerateAuthenticateHeader_cb_delegate == null)
					GenerateAuthenticateHeader_cb_delegate = new GenerateAuthenticateHeaderNativeDelegate (GenerateAuthenticateHeader_cb);
				return GenerateAuthenticateHeader_cb_delegate;
			}
		}

		static void OverrideGenerateAuthenticateHeader (GLib.GType gtype)
		{
			OverrideGenerateAuthenticateHeader (gtype, GenerateAuthenticateHeaderVMCallback);
		}

		static void OverrideGenerateAuthenticateHeader (GLib.GType gtype, GenerateAuthenticateHeaderNativeDelegate callback)
		{
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) gtype.GetClassPtr()) + (long) class_abi.GetFieldOffset("generate_authenticate_header"));
				*raw_ptr = Marshal.GetFunctionPointerForDelegate((Delegate) callback);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate void GenerateAuthenticateHeaderNativeDelegate (IntPtr inst, IntPtr ctx);

		static void GenerateAuthenticateHeader_cb (IntPtr inst, IntPtr ctx)
		{
			try {
				RTSPAuth __obj = GLib.Object.GetObject (inst, false) as RTSPAuth;
				__obj.OnGenerateAuthenticateHeader (Gst.RtspServer.RTSPContext.New (ctx));
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, false);
			}
		}

		[GLib.DefaultSignalHandler(Type=typeof(Gst.RtspServer.RTSPAuth), ConnectionMethod="OverrideGenerateAuthenticateHeader")]
		protected virtual void OnGenerateAuthenticateHeader (Gst.RtspServer.RTSPContext ctx)
		{
			InternalGenerateAuthenticateHeader (ctx);
		}

		private void InternalGenerateAuthenticateHeader (Gst.RtspServer.RTSPContext ctx)
		{
			GenerateAuthenticateHeaderNativeDelegate unmanaged = null;
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) this.LookupGType().GetThresholdType().GetClassPtr()) + (long) class_abi.GetFieldOffset("generate_authenticate_header"));
				unmanaged = (GenerateAuthenticateHeaderNativeDelegate) Marshal.GetDelegateForFunctionPointer(*raw_ptr, typeof(GenerateAuthenticateHeaderNativeDelegate));
			}
			if (unmanaged == null) return;

			IntPtr native_ctx = GLib.Marshaller.StructureToPtrAlloc (ctx);
			unmanaged (this.Handle, native_ctx);
			Marshal.FreeHGlobal (native_ctx);
		}

		static AcceptCertificateNativeDelegate AcceptCertificate_cb_delegate;
		static AcceptCertificateNativeDelegate AcceptCertificateVMCallback {
			get {
				if (AcceptCertificate_cb_delegate == null)
					AcceptCertificate_cb_delegate = new AcceptCertificateNativeDelegate (AcceptCertificate_cb);
				return AcceptCertificate_cb_delegate;
			}
		}

		static void OverrideAcceptCertificate (GLib.GType gtype)
		{
			OverrideAcceptCertificate (gtype, AcceptCertificateVMCallback);
		}

		static void OverrideAcceptCertificate (GLib.GType gtype, AcceptCertificateNativeDelegate callback)
		{
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) gtype.GetClassPtr()) + (long) class_abi.GetFieldOffset("accept_certificate"));
				*raw_ptr = Marshal.GetFunctionPointerForDelegate((Delegate) callback);
			}
		}

		[UnmanagedFunctionPointer (CallingConvention.Cdecl)]
		delegate bool AcceptCertificateNativeDelegate (IntPtr inst, IntPtr connection, IntPtr peer_cert, int errors);

		static bool AcceptCertificate_cb (IntPtr inst, IntPtr connection, IntPtr peer_cert, int errors)
		{
			try {
				RTSPAuth __obj = GLib.Object.GetObject (inst, false) as RTSPAuth;
				bool __result;
				__result = __obj.OnAcceptCertificate (GLib.Object.GetObject(connection) as GLib.TlsConnection, GLib.Object.GetObject(peer_cert) as GLib.TlsCertificate, (GLib.TlsCertificateFlags) errors);
				return __result;
			} catch (Exception e) {
				GLib.ExceptionManager.RaiseUnhandledException (e, true);
				// NOTREACHED: above call does not return.
				throw e;
			}
		}

		[GLib.DefaultSignalHandler(Type=typeof(Gst.RtspServer.RTSPAuth), ConnectionMethod="OverrideAcceptCertificate")]
		protected virtual bool OnAcceptCertificate (GLib.TlsConnection connection, GLib.TlsCertificate peer_cert, GLib.TlsCertificateFlags errors)
		{
			return InternalAcceptCertificate (connection, peer_cert, errors);
		}

		private bool InternalAcceptCertificate (GLib.TlsConnection connection, GLib.TlsCertificate peer_cert, GLib.TlsCertificateFlags errors)
		{
			AcceptCertificateNativeDelegate unmanaged = null;
			unsafe {
				IntPtr* raw_ptr = (IntPtr*)(((long) this.LookupGType().GetThresholdType().GetClassPtr()) + (long) class_abi.GetFieldOffset("accept_certificate"));
				unmanaged = (AcceptCertificateNativeDelegate) Marshal.GetDelegateForFunctionPointer(*raw_ptr, typeof(AcceptCertificateNativeDelegate));
			}
			if (unmanaged == null) return false;

			bool __result = unmanaged (this.Handle, connection == null ? IntPtr.Zero : connection.Handle, peer_cert == null ? IntPtr.Zero : peer_cert.Handle, (int) errors);
			return __result;
		}


		// Internal representation of the wrapped structure ABI.
		static GLib.AbiStruct _class_abi = null;
		static public new GLib.AbiStruct class_abi {
			get {
				if (_class_abi == null)
					_class_abi = new GLib.AbiStruct (new List<GLib.AbiField>{ 
						new GLib.AbiField("authenticate"
							, GLib.Object.class_abi.Fields
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // authenticate
							, null
							, "check"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("check"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // check
							, "authenticate"
							, "generate_authenticate_header"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("generate_authenticate_header"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // generate_authenticate_header
							, "check"
							, "accept_certificate"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("accept_certificate"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // accept_certificate
							, "generate_authenticate_header"
							, "_gst_reserved"
							, (uint) Marshal.SizeOf(typeof(IntPtr))
							, 0
							),
						new GLib.AbiField("_gst_reserved"
							, -1
							, (uint) Marshal.SizeOf(typeof(IntPtr)) * 3 // _gst_reserved
							, "accept_certificate"
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
		static extern IntPtr gst_rtsp_auth_get_type();

		public static new GLib.GType GType { 
			get {
				IntPtr raw_ret = gst_rtsp_auth_get_type();
				GLib.GType ret = new GLib.GType(raw_ret);
				return ret;
			}
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_rtsp_auth_check(IntPtr check);

		public static bool Check(string check) {
			IntPtr native_check = GLib.Marshaller.StringToPtrGStrdup (check);
			bool raw_ret = gst_rtsp_auth_check(native_check);
			bool ret = raw_ret;
			GLib.Marshaller.Free (native_check);
			return ret;
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_rtsp_auth_make_basic(IntPtr user, IntPtr pass);

		public static string MakeBasic(string user, string pass) {
			IntPtr native_user = GLib.Marshaller.StringToPtrGStrdup (user);
			IntPtr native_pass = GLib.Marshaller.StringToPtrGStrdup (pass);
			IntPtr raw_ret = gst_rtsp_auth_make_basic(native_user, native_pass);
			string ret = GLib.Marshaller.PtrToStringGFree(raw_ret);
			GLib.Marshaller.Free (native_user);
			GLib.Marshaller.Free (native_pass);
			return ret;
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_add_basic(IntPtr raw, IntPtr basic, IntPtr token);

		public void AddBasic(string basic, Gst.RtspServer.RTSPToken token) {
			IntPtr native_basic = GLib.Marshaller.StringToPtrGStrdup (basic);
			gst_rtsp_auth_add_basic(Handle, native_basic, token == null ? IntPtr.Zero : token.Handle);
			GLib.Marshaller.Free (native_basic);
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_add_digest(IntPtr raw, IntPtr user, IntPtr pass, IntPtr token);

		public void AddDigest(string user, string pass, Gst.RtspServer.RTSPToken token) {
			IntPtr native_user = GLib.Marshaller.StringToPtrGStrdup (user);
			IntPtr native_pass = GLib.Marshaller.StringToPtrGStrdup (pass);
			gst_rtsp_auth_add_digest(Handle, native_user, native_pass, token == null ? IntPtr.Zero : token.Handle);
			GLib.Marshaller.Free (native_user);
			GLib.Marshaller.Free (native_pass);
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_rtsp_auth_get_default_token(IntPtr raw);

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_set_default_token(IntPtr raw, IntPtr token);

		public Gst.RtspServer.RTSPToken DefaultToken { 
			get {
				IntPtr raw_ret = gst_rtsp_auth_get_default_token(Handle);
				Gst.RtspServer.RTSPToken ret = raw_ret == IntPtr.Zero ? null : (Gst.RtspServer.RTSPToken) GLib.Opaque.GetOpaque (raw_ret, typeof (Gst.RtspServer.RTSPToken), true);
				return ret;
			}
			set {
				gst_rtsp_auth_set_default_token(Handle, value == null ? IntPtr.Zero : value.Handle);
			}
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_rtsp_auth_get_realm(IntPtr raw);

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_set_realm(IntPtr raw, IntPtr realm);

		public string Realm { 
			get {
				IntPtr raw_ret = gst_rtsp_auth_get_realm(Handle);
				string ret = GLib.Marshaller.PtrToStringGFree(raw_ret);
				return ret;
			}
			set {
				IntPtr native_value = GLib.Marshaller.StringToPtrGStrdup (value);
				gst_rtsp_auth_set_realm(Handle, native_value);
				GLib.Marshaller.Free (native_value);
			}
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern int gst_rtsp_auth_get_supported_methods(IntPtr raw);

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_set_supported_methods(IntPtr raw, int methods);

		public Gst.Rtsp.RTSPAuthMethod SupportedMethods { 
			get {
				int raw_ret = gst_rtsp_auth_get_supported_methods(Handle);
				Gst.Rtsp.RTSPAuthMethod ret = (Gst.Rtsp.RTSPAuthMethod) raw_ret;
				return ret;
			}
			set {
				gst_rtsp_auth_set_supported_methods(Handle, (int) value);
			}
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern int gst_rtsp_auth_get_tls_authentication_mode(IntPtr raw);

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_set_tls_authentication_mode(IntPtr raw, int mode);

		public GLib.TlsAuthenticationMode TlsAuthenticationMode { 
			get {
				int raw_ret = gst_rtsp_auth_get_tls_authentication_mode(Handle);
				GLib.TlsAuthenticationMode ret = (GLib.TlsAuthenticationMode) raw_ret;
				return ret;
			}
			set {
				gst_rtsp_auth_set_tls_authentication_mode(Handle, (int) value);
			}
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_rtsp_auth_get_tls_certificate(IntPtr raw);

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_set_tls_certificate(IntPtr raw, IntPtr cert);

		public GLib.TlsCertificate TlsCertificate { 
			get {
				IntPtr raw_ret = gst_rtsp_auth_get_tls_certificate(Handle);
				GLib.TlsCertificate ret = GLib.Object.GetObject(raw_ret, true) as GLib.TlsCertificate;
				return ret;
			}
			set {
				gst_rtsp_auth_set_tls_certificate(Handle, value == null ? IntPtr.Zero : value.Handle);
			}
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern IntPtr gst_rtsp_auth_get_tls_database(IntPtr raw);

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_set_tls_database(IntPtr raw, IntPtr database);

		public GLib.TlsDatabase TlsDatabase { 
			get {
				IntPtr raw_ret = gst_rtsp_auth_get_tls_database(Handle);
				GLib.TlsDatabase ret = GLib.Object.GetObject(raw_ret, true) as GLib.TlsDatabase;
				return ret;
			}
			set {
				gst_rtsp_auth_set_tls_database(Handle, value == null ? IntPtr.Zero : value.Handle);
			}
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern bool gst_rtsp_auth_parse_htdigest(IntPtr raw, IntPtr path, IntPtr token);

		public bool ParseHtdigest(string path, Gst.RtspServer.RTSPToken token) {
			IntPtr native_path = GLib.Marshaller.StringToFilenamePtr (path);
			bool raw_ret = gst_rtsp_auth_parse_htdigest(Handle, native_path, token == null ? IntPtr.Zero : token.Handle);
			bool ret = raw_ret;
			GLib.Marshaller.Free (native_path);
			return ret;
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_remove_basic(IntPtr raw, IntPtr basic);

		public void RemoveBasic(string basic) {
			IntPtr native_basic = GLib.Marshaller.StringToPtrGStrdup (basic);
			gst_rtsp_auth_remove_basic(Handle, native_basic);
			GLib.Marshaller.Free (native_basic);
		}

		[DllImport("gstrtspserver-1.0-0.dll", CallingConvention = CallingConvention.Cdecl)]
		static extern void gst_rtsp_auth_remove_digest(IntPtr raw, IntPtr user);

		public void RemoveDigest(string user) {
			IntPtr native_user = GLib.Marshaller.StringToPtrGStrdup (user);
			gst_rtsp_auth_remove_digest(Handle, native_user);
			GLib.Marshaller.Free (native_user);
		}


		static RTSPAuth ()
		{
			GtkSharp.GstreamerSharp.ObjectManager.Initialize ();
		}

		// Internal representation of the wrapped structure ABI.
		static GLib.AbiStruct _abi_info = null;
		static public new GLib.AbiStruct abi_info {
			get {
				if (_abi_info == null)
					_abi_info = new GLib.AbiStruct (new List<GLib.AbiField>{ 
						new GLib.AbiField("priv"
							, GLib.Object.abi_info.Fields
							, (uint) Marshal.SizeOf(typeof(IntPtr)) // priv
							, null
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
