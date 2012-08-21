class CreateWordSearches < ActiveRecord::Migration
  def change
    create_table :word_searches do |t|
      t.Fixnum :width
      t.Fixnum :height
      t.String :board

      t.timestamps
    end
  end
end
