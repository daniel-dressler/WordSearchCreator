class WsWordList < ActiveRecord::Base
  	belongs_to :WordSearchSet
  	attr_accessible :words

  	def set(words)
	  	@words = words.split(/;/).sort!().join(";")
  	end
	
	def to_s
		@words
	end
end
