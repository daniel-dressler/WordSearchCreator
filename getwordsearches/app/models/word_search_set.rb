class WordSearchSet < ActiveRecord::Base
  has_one :prototype
  has_one :goal
  has_one :swears
  has_one :words
  has_many :grids
  has_one :alphabet
  
  def initialize(goal)
	  #self.goal = goal
  end
  
  def addWordsAndSwears(words, swears)
	  #cleaner = { |s| s
	 @words = Word.new(words) 
	 @sweats = Words.new(swears)
	 
  end
  
  def to_pdf
	  
  end
end
