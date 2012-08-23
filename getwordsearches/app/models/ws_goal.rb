class WsGoal < ActiveRecord::Base
  belongs_to :difficulty
  belongs_to :set
  attr_accessible :date?, :due, :name?, :title
end
