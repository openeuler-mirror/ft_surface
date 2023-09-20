#!/bin/bash

rm -rf ~/rpmbuild
rm -rf ~/tmp
rm -rf ft_surface_wrapper/build
mkdir ~/tmp/
cp -r ft_surface_wrapper ft_surface_wrapper-1.0.0
tar -zcv -f ~/tmp/ft_surface_wrapper-1.0.0.tar.gz ft_surface_wrapper-1.0.0
cp ft_surface_wrapper.spec ~/tmp/
rm -r ft_surface_wrapper-1.0.0
cd ~/tmp/
rpmbuild -bb -D "_sourcedir`pwd`" *.spec --nodeps
