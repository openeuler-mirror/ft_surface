Name:   ft_surface_wrapper
Version:  1.0.0
Release:  1%{?dist}
Summary:  fangtian engine surface wrapper for mesa
License:  Apache-2.0
URL:    https://gitee.com/ShaoboFeng/ft_surface_wrapper
Source0:  %{name}-%{version}.tar.gz

Requires:    cmake
%prep
%setup -q

%build
mkdir build && cd build
%{cmake3} ..
%make_build

%install
cd build
%make_install

%files
%{_libdir}/lib%{name}.so*
%{_libdir}/pkgconfig/ft_surface_wrapper.pc
%dir %{_includedir}/ftsurface
%{_includedir}/ftsurface/buffer_handle.h
%{_includedir}/ftsurface/display_type.h
%{_includedir}/ftsurface/external_window.h
%{_includedir}/ftsurface/native_window_wrapper.h
%{_includedir}/ftsurface/window.h

%description
ft_surface_wrapper is wrapper for fangtian surface module in ft_engine. this lib is used for build mesa with ohos platform.

%changelog
* Tue Jul 11 2023 fengshaobo  - 1.0.0
- first version for ft_surface_wrapper
