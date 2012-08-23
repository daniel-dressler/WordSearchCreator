class WordSearchSet < ActiveRecord::Base
  belongs_to :prototype
  belongs_to :goal
  belongs_to :swears
  belongs_to :words
  belongs_to :grids
  belongs_to :alphabet
  # attr_accessible :title, :body
end
