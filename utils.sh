COMMAND="$1"
case "$COMMAND" in
    'sync-version')
        version=`/usr/libexec/PlistBuddy -c "Print CFBundleShortVersionString" MovieousShortVideo.framework/Info.plist`
        cd MovieousShortVideoDemo
        agvtool new-marketing-version $version
        pod update --no-repo-update
        cd ..
        git add .
        git commit -m "release v$version"
        git tag "v$version"
        git push
        git push --tags
        exit 0
        ;;
    'get-version')
        echo `/usr/libexec/PlistBuddy -c "Print CFBundleShortVersionString" MovieousShortVideo.framework/Info.plist`
        ;;
    *)
        echo "Unknown command $COMMAND"
        usage
        exit 1
        ;;
esac
