class CreateWordSelections < ActiveRecord::Migration
  def change
    create_table :word_selections do |t|
      t.string :words

      t.timestamps
    end
  end
end
