class CreateWsAlphas < ActiveRecord::Migration
  def change
    create_table :ws_alphas do |t|
      t.string :chars
      t.references :word_search_set

      t.timestamps
    end
    add_index :ws_alphas, :word_search_set_id
  end
end
