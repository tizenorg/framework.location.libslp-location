Name: libslp-location
Summary: Location Based Service
Version: 0.11.6
Release: 1
Group: Framework/Location
License: Apache-2.0
Source0: %{name}-%{version}.tar.gz
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  cmake
BuildRequires:  model-build-features
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gmodule-2.0)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(capi-appfw-app-manager)
BuildRequires:  pkgconfig(capi-appfw-package-manager)
BuildRequires:  pkgconfig(pkgmgr-info)
%if "%{?tizen_profile_name}" != "tv"
BuildRequires:  pkgconfig(privacy-manager-client)
%endif
BuildRequires:  pkgconfig(json-glib-1.0)
BuildRequires:  pkgconfig(bundle)
BuildRequires:  pkgconfig(eventsystem)

%description
Location Based Service Libraries


%package devel
Summary:	Location Based Service (Development files)
Group:		System/Libraries
Requires:	%{name} = %{version}-%{release}

%description devel
Location Based Service Development Package


%prep
%setup -q -n %{name}-%{version}


%build
export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_DEBUG_ENABLE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE"

# Call make instruction with smp support
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER} \
%if "%{?tizen_profile_name}" == "wearable"
	-DFEATURE_PROFILE_WEARABLE:BOOL=ON \
%endif
%if "%{?tizen_profile_name}" == "tv"
	-DFEATURE_PROFILE_TV:BOOL=ON
%endif



make %{?jobs:-j%jobs}


%install
rm -rf %{buildroot}
%make_install


%clean
rm -rf %{buildroot}


%post
/sbin/ldconfig


%postun -p /sbin/ldconfig


%files
%manifest libslp-location.manifest
%{_libdir}/lib*.so*


%files devel
%{_includedir}/location/*.h
%{_libdir}/pkgconfig/*.pc
