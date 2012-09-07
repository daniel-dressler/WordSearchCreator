class WsPrototype < ActiveRecord::Base
  belongs_to :set, :class_name => 'WordSearchSet'
  attr_accessor :height, :seed, :width
  
  def initialize()
	  @seed = Time.now.to_i
  end
end
