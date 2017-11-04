# Teapot v2.2.0 configuration generated at 2017-11-04 15:27:36 +1300

required_version "2.0"

# Project Metadata

define_project "statistics" do |project|
	project.title = "Statistics"
	project.summary = 'A brief one line summary of the project.'
	
	project.description = <<-EOF
		Statistics description.
	EOF
	
	project.license = 'MIT License'
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	# project.website = 'http://Statistics.com/'
	
	project.version = '0.1.0'
end

# Build Targets

define_target 'statistics-library' do |target|
	target.build do
		source_root = target.package.path + 'source'
		copy headers: source_root.glob('Statistics/**/*.{h,hpp}')
		build static_library: 'Statistics', source_files: source_root.glob('Statistics/**/*.cpp')
	end
	
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends 'Language/C++14', private: true
	
	target.provides 'Library/Statistics' do
		append linkflags [
			->{install_prefix + 'lib/libStatistics.a'},
		]
	end
end

define_target 'statistics-test' do |target|
	target.build do |*arguments|
		test_root = target.package.path + 'test'
		
		run tests: 'Statistics', source_files: test_root.glob('Statistics/**/*.cpp'), arguments: arguments
	end
	
	target.depends 'Library/UnitTest'
	target.depends 'Library/Statistics'
	
	target.provides 'Test/Statistics'
end

define_target 'statistics-executable' do |target|
	target.build do
		source_root = target.package.path + 'source'
		
		build executable: 'Statistics', source_files: source_root.glob('Statistics.cpp')
	end
	
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends 'Language/C++14', private: true
	
	target.depends 'Library/Statistics'
	target.provides 'Executable/Statistics'
end

define_target 'statistics-run' do |target|
	target.build do |*arguments|
		run executable: 'Statistics', arguments: arguments
	end
	
	target.depends 'Executable/Statistics'
	target.provides 'Run/Statistics'
end

# Configurations

define_configuration 'development' do |configuration|
	configuration[:source] = "https://github.com/kurocha"
	configuration.import "statistics"
	
	# Provides all the build related infrastructure:
	configuration.require 'platforms'
	
	# Provides unit testing infrastructure and generators:
	configuration.require 'unit-test'
	
	# Provides some useful C++ generators:
	configuration.require 'generate-cpp-class'
	
	configuration.require "generate-project"
	configuration.require "generate-travis"
end

define_configuration "statistics" do |configuration|
	configuration.public!
end
