Pod::Spec.new do |spec|
  spec.ios.deployment_target = '8.0'
  spec.name         = 'MovieousShortVideo-CN'
  spec.version      = `sh utils.sh get-version`
  spec.homepage     = 'https://movieous-team.coding.net/p/MovieousShortVideo-Cocoa/d/MovieousShortVideo-Cocoa/git'
  spec.authors      = { 'movieous' => 'cloudop@movieous.video' }
  spec.summary      = 'Movieous short video SDK for iOS.'
  spec.source       = { :git => 'https://e.coding.net/movieous-team/MovieousShortVideo-Cocoa.git', :tag => "v#{spec.version}" }
  spec.static_framework = true
  spec.vendored_frameworks = 'MovieousShortVideo.framework'
  spec.libraries    = 'c++', 'resolv'
  spec.dependency 'MovieousCaptureBase-CN', '3.0.0'
end