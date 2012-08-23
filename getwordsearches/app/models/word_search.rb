class WordSearch < ActiveRecord::Base
  attr_accessible :board, :height, :widt
  has_one :WordSelection
end
