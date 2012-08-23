class WsWordList < ActiveRecord::Base
  belongs_to :set
  attr_accessible :words
end
