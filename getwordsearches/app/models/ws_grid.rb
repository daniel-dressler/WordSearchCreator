class WsGrid < ActiveRecord::Base
  belongs_to :set
  attr_accessible :grid
  def initialize(angles, words, swears, seed)
 	@grid = `lib/algo/algo 5 5 255 5 "a;this;fun;life;seven;" 1 "fuck;" 1231`; 
  end
end
