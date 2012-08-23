class WsAlpha < ActiveRecord::Base
  belongs_to :set
  attr_accessible :chars
end
