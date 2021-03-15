#ifndef ECS_H
#define ECS_H


namespace ecs
{

    // init with HERO_ENTITY_ID = 0
    std::vector<int> ENTITIES = {HERO_ENTITY_ID};

    // creates new entity id and adds it to entities
    int get_new_entity_id()
    {
        logg::print("Making new ID",1);
        int new_id =  ecs::ENTITIES.back() + 1;
        ecs::ENTITIES.push_back(new_id);
        return new_id;
    }

    // returns index of given entity_id in the vector
    int get_index_of_entity(int entity_id, std::vector<int> &dest_index)
    {
        int default_int = 999;
        if (dest_index.size() > 0)
        {
            for(int i=0; i < dest_index.size(); i++)
            {
                if(dest_index[i] == entity_id)
                {
                    default_int = i;
                    break;
                }

            }
            return default_int;    
        }   else 
        {
            return default_int;
        }
    };

    // finds entity id in table of structs
    template<typename T>
    int get_index_of_struct_entity(int entity_id, std::vector<T> &dest_vector)
    {
        int default_int = 999;
        if (dest_vector.size() > 0)
        {
            for(int i=0; i < dest_vector.size(); i++)
            {
                if(dest_vector[i].ENTITY_ID == entity_id)
                {
                    default_int = i;
                    break;
                }

            }
            return default_int;    
        }   else 
        {
            return default_int;
        }
    };

    // move entity from one state to another, optional remove from previous one
    void change_entity_state(int entity_id, 
                        std::vector<int> &source_index, 
                        std::vector<int> &dest_index,
                        bool delete_in_source)
    {
        dest_index.push_back(entity_id); 
        if(delete_in_source)
        {
            int source_entity_id_index = ecs::get_index_of_entity(entity_id, source_index);
            source_index.erase(source_index.begin() + source_entity_id_index);
        }
    };



    void sort_vector(std::vector<int> &v)
    {
        sort(v.begin(), v.end()); 
    }

    void sort_vector_decreasing(std::vector<int> &v)
    {
        sort(v.begin(), v.end(), std::greater<int>()); 
    }

        
    void print_vector(const  std::vector<int> &v, std::string name)
    {
        if(v.size()>0)
        {
            std::cout << name;
            for(int i = 0; i < v.size(); i++)
            {
                std::cout << v[i] << ",";
            }
            std::cout << std::endl;
        }

    }

    void remove_vector_duplicates(std::vector<int> &v)
    {
        if(v.size() > 0)
        {
            // remove duplicates
            std::sort(v.begin(), v.end());
            auto last = std::unique(v.begin(), v.end());
            v.erase(last, v.end()); 
        }   
    }


    struct compare
    {
        int key;
        compare(int const &i): key(i) { }
        bool operator()(int const &i)
        {
            return (i == key);
        }
    };

    int get_index_of_min(int array[])
    {
        int index = 0;
        for(int i = 1; i < 8; i++)
        {
            if(array[i] < array[index])
                index = i;              
        }
        return index;
    }

    template<typename T>
    void delete_from_vector_by_index(int index, std::vector<T> &v)
    {
        v.erase(v.begin() + index);
    };


    template<typename T>
    int get_index_of_struct_level(int level_id, std::vector<T> &dest_vector)
    {
        int default_int = 999;
        if (dest_vector.size() > 0)
        {
            for(int i=0; i < dest_vector.size(); i++)
            {
                if(dest_vector[i].level_id == level_id)
                {
                    default_int = i;
                    break;
                }

            }
            return default_int;    
        }   else 
        {
            return default_int;
        }
    };


    int get_index_of_int_vector(int value, std::vector<int> &v)
    {
        int index = 999;
        for(int i = 0; i < v.size(); i++)
        {
            if(value == v[i])
            {
                index = i;
                break;
            }

        }
        return index;

    }

}

#endif