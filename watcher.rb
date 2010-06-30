require 'rubygems'
require 'fssm'

FSSM.monitor('.', '**/*.cpp') do
  update {|base, relative| system 'make'}
  delete {|base, relative|}
  create {|base, relative|}
end
