Name:		libslp-location
Summary:	Location Based Service
Version:	0.9.0
Release:	1
Group:		System/Libraries
License:	TBD
Source0:	%{name}-%{version}.tar.gz
Requires(post):  /sbin/ldconfig
Requires(post):  /usr/bin/vconftool
Requires(postun):  /sbin/ldconfig
BuildRequires:  cmake
BuildRequires:  model-build-features
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gmodule-2.0)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(capi-appfw-app-manager)
BuildRequires:  pkgconfig(capi-appfw-package-manager)
BuildRequires:  pkgconfig(pkgmgr-info)
BuildRequires:  pkgconfig(privacy-manager-client)
BuildRequires:  pkgconfig(json-glib-1.0)
BuildRequires:  pkgconfig(lbs-dbus)

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
#%if "%{_repository}" == "wearable“
#export CFLAGS="$CFLAGS -DTIZEN_WEARABLE"
#%endif

# Call make instruction with smp support
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}


%install
rm -rf %{buildroot}
%make_install


%clean
rm -rf %{buildroot}


%post
/sbin/ldconfig
vconftool set -t int memory/location/last/gps/Timestamp "0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/gps/Latitude "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/gps/Longitude "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/gps/Altitude "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/gps/HorAccuracy "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/gps/VerAccuracy "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/gps/Speed "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/gps/Direction "0.0" -i -f -s location_fw::client
vconftool set -t int memory/location/last/wps/Timestamp "0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/wps/Latitude "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/wps/Longitude "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/wps/Altitude "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/wps/HorAccuracy "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/wps/Speed "0.0" -i -f -s location_fw::client
vconftool set -t double memory/location/last/wps/Direction "0.0" -i -f -s location_fw::client

vconftool set -t int db/location/last/gps/LocTimestamp "0" -f -s location_fw::client
vconftool set -t int db/location/last/wps/LocTimestamp "0" -f -s location_fw::client
vconftool set -t string db/location/last/gps/Location "0.0;0.0;0.0;0.0;0.0;0.0;0.0;" -f -s location_fw::client
vconftool set -t string db/location/last/wps/Location "0.0;0.0;0.0;0.0;0.0;0.0;" -f -s location_fw::client

vconftool set -t int db/location/setting/Usemylocation "1" -g 6514 -f -s location_fw::vconf
vconftool set -t int db/location/setting/GpsEnabled "1" -g 6514 -f -s location_fw::vconf
vconftool set -t int db/location/setting/AgpsEnabled "0" -g 6514 -f -s location_fw::vconf
vconftool set -t int db/location/setting/GpsPopup "1" -g 6514 -f -s system::vconf_network

%if 0%{?model_build_feature_location_position_wps}
vconftool set -t int db/location/setting/NetworkEnabled "1" -g 6514 -f -s location_fw::vconf
%else
vconftool set -t int db/location/setting/NetworkEnabled "0" -g 6514 -f -s location_fw::vconf
%endif

%postun -p /sbin/ldconfig


%files
%manifest libslp-location.manifest
%{_libdir}/lib*.so*


%files devel
%{_includedir}/location/*.h
%{_libdir}/pkgconfig/*.pc
