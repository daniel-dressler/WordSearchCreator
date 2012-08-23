class WsPrototype < ActiveRecord::Base
  belongs_to :set
  attr_accessible :height, :seed, :width
end
