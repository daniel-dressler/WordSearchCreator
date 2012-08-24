class WsWordList < ActiveRecord::Base
  belongs_to :set
  attr_accessible :words
  
  def initialize(words)
	  @words = words.split(/;/).sort!().join(";")
  end
end
