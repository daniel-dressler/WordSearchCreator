class WsGoal < ActiveRecord::Base
  	belongs_to :set, :class_name => 'WordSearchSet'
  	attr_accessor :date, :due, :name, :title, :copies, :angles

  	def set(copies, angles)
		@copies, @angles = copies, angles
  	end
end
