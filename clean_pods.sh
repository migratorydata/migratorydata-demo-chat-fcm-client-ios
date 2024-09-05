pod deintegrate
pod cache clean --all
rm -rf Pods/
rm Podfile.lock
pod install
