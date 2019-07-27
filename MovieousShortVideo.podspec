Pod::Spec.new do |spec|
  spec.ios.deployment_target = '8.0'
  spec.name         = 'MovieousShortVideo'
  spec.version      = `sh utils.sh get-version`
  spec.homepage     = 'https://github.com/movieous-team/MovieousShortVideo-Cocoa-Release'
  spec.authors      = { 'movieous' => 'cloudop@movieous.video' }
  spec.summary      = 'Movieous short video SDK for iOS.'
  spec.source       = { :git => 'https://github.com/movieous-team/MovieousShortVideo-Cocoa-Release.git', :tag => "v#{spec.version}" }
  spec.static_framework = true
  spec.vendored_frameworks = 'MovieousShortVideo.framework'
  spec.libraries    = 'c++', 'resolv'
  spec.dependency 'MovieousBase', '~> 1.1.4'
end