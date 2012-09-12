class WsPrototype < ActiveRecord::Base
  belongs_to :set, :class_name => 'WordSearchSet'
  attr_accessor :height, :seed, :width
  
  def set(height, width)
	  @height, @width = height, width
	  @seed = Time.now.to_i
  end
end
