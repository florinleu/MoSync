#!/usr/bin/ruby

require File.expand_path('../../rules/mosync_lib.rb')

mod = Module.new
mod.class_eval do
	def setup_native
		@LOCAL_DLLS = ["mosync", "mastd", "mautil"]
		setup_base
	end

	def setup_pipe
		setup_base
	end

	def setup_base
		@SOURCES = [".", "Contacts"]
		@EXTRA_INCLUDES = ['.']

		copyFilesSubDir("Contacts")

		#@IGNORED_HEADERS = ["pim.h"]
		@HEADER_DIRS = ['.']
		@INSTALL_INCDIR = "pim"
		@NAME = "pim"
	end

	def copyFilesSubDir(name)
		@INSTALL_INCDIR = "pim/" + name
		@HEADER_DIRS = [name]
		copyHeaders
	end

end

MoSyncLib.invoke(mod)
