class WsGoal < ActiveRecord::Base
  	belongs_to :set, :class_name => 'WordSearchSet'
  	attr_accessor :date, :due, :name, :title, :copies

  	def set(copies)
		@copies = copies
  	end
end
