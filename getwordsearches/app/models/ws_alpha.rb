class WsAlpha < ActiveRecord::Base
  belongs_to :set
  attr_accessible :chars
  
  def initialize(chars)
	  @chars = chars;
  end
end
