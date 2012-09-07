class WsGrid < ActiveRecord::Base
  	belongs_to :set, :class_name => 'WordSearchSet'
  	attr_accessor :grid
  	def initialize(set)
 		@grid = `lib/algo/algo 5 5 255 5 "#{set.words.to_s}" 1 "#{set.swears.to_s}" 1231`; 
  	end
end
