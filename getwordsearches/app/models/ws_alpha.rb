class WsAlpha < ActiveRecord::Base
  belongs_to :set
  attr_accessible :chars
  
  def set(chars)
	  @chars = chars;
  end
end
