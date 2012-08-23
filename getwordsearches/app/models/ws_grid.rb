class WsGrid < ActiveRecord::Base
  belongs_to :set
  attr_accessible :grid
end
