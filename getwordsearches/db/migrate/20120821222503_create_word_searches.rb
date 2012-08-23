class CreateWordSearches < ActiveRecord::Migration
  def change
    create_table :word_searches do |t|
      t.integer :width
      t.integer :height
      t.string :board

      t.timestamps
    end
  end
end
