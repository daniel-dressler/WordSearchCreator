class WsWordList < ActiveRecord::Base
  	belongs_to :set, :class_name => 'WordSearchSet'
  	attr_accessible :words

  	def set(words)
	  	@words = words.split(/;/).sort!().join(";")
  	end
end
