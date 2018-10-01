#
# Example spec file for cdplayer app...
#
Name: mutabor
Summary: Retuning MIDI instruments for complex microtonal tunings
Version: 4.0.0~rc3
Release: 1
License: GPL
Group: Productivity/Multimedia/Sound/Midi
Source: https://github.com/keinstein/mutabor/releases/download/debian%2F4.0.0_rc3-1/mutabor_4.0.0.rc3.orig.tar.gz
URL: http://www.math.tu-dresden.de/~mutabor/
#Distribution: OpenSuse
Vendor: TU Dresden, Institut für Algebra
#Packager: Tobias.Schlemmer <keinstein@users.berlios.de>
BuildRoot:    %{_tmppath}/%{name}-%{version}-build
Prefix:       %{_prefix}
BuildRequires: wxWidgets-devel, alsa-devel, boost-devel >= 1.53.0 , gcc-c++, cppunit-devel, tex4ht, bison, flex, autopoint, libexpat-devel, autoconf >= 2.67, pkg-config >= 0.14.0, gettext >= 0.19

%description
Mutabor is a program that allows a musician to perform real time Music with
arbitray posibly infinite tone systems. The program uses the Pitch Bend
functinality of your MIDI instrument to reach very fast retunings. With the
help of a control file it is possible to write complex tunings and even tuning
logics, which change the tuning according chords, forms of chords, keys and
other events. It is faster and more powerful than most equipment on the
market, exspecially in the low cost segment.
.
The pitchbend functinality allows a precition of the 8192th part (factor
0.000122) of the pitch bend range. In GM standard this is about 0.0244 cents.
.
This package contains the main program.


%package doc
Summary:      Documentation for %{name}
Group:        Productivity/Multimedia/Sound/Midi

%description doc
This package contains the documentation for %{name}.

%define docs %{_defaultdocdir}/%{name}
%define docsub %{docs}/doc

# %setup is a macro setting up what we need


%prep
umask 022
test -n '%{buildroot}' || { echo "Must use buildroot" ; exit 1 ; }
%if %{?fake:%fake}%{!?fake:0}
%setup -T -D -n %{name}-%{version}
%else
%setup -q -n %{name}-%{version}
test -d %{name}-%{version} && mv %{name}-%{version}/* .
test -d %{name} && mv %{name}/* .
%endif

%build
umask 022
cd "$RPM_BUILD_DIR"/%{name}-%{version}
%if %{?fake:%fake}%{!?fake:0}
%else
%configure --enable-static --enable-shared
make %{?_smp_mflags} glibmm_docdir=%{docsub} gtkmm_docdir=%{docsub}
find . -name "*.so*" -type f -not -name \*.source | xargs strip --strip-unneeded mutabor
%endif


%install
umask 022
rm -rf $RPM_BUILD_ROOT
mkdir $RPM_BUILD_ROOT
cd "$RPM_BUILD_DIR"/%{name}-%{version}
test -n '%{buildroot}'
test -d '%{buildroot}' && rm -rf '%{buildroot}'
install -d -m 755 '%{buildroot}%{docsub}'
install -p -m 644 AUTHORS ChangeLog COPYING NEWS README '%{buildroot}%{docs}'
%make_install
%find_lang  mutabor

%files -f %{name}.lang
%defattr(-,root,root)
%dir %{docs}
%{docs}/AUTHORS
%{docs}/ChangeLog
%{docs}/COPYING
%{docs}/NEWS
%{docs}/README
%{_bindir}/mutabor
%{_datadir}/mutabor
%{_mandir}/*/mutabor.*

# Requires

#%post
#%update_menus: 

%files doc
%defattr(-,root,root)
%dir %{docs}
%doc ChangeLog
%doc %{_datadir}/doc/mutabor
%{docsub}

%changelog
* Sun Apr 15 2012 Tobias Schlemmmer <keinstein@users.berlios.de>
- built from scratch with version 4.0.0beta1
